/*
 * Project DiabetesHealthDevice
 * Description: Predicting diabetes risk using a machine learning algorithm
 * Author: Sumit Kumar @neuton.ai
 * Date: 06/10/2022
 */

#include "Particle.h"
#include <ArduinoJson.h>
#include "neuton.h"

// Forward declarations
void getDataHandler(const char *topic, const char *data);
void publishPredictionData(uint16_t index, unsigned long inference_time, float* outputs);

char text[256];
String payload ="";

input_t inputs[8];

unsigned long start;
unsigned long stop;
unsigned long inference_time;

const unsigned long CHECK_PERIOD_MS = 15000;
const unsigned long FIRST_CHECK_MS = 5000;
const char *CHECK_EVENT_NAME = "diabetes-get";
const char *PUBLISH_EVENT_NAME = "diabetes-put";

unsigned long lastPublish = FIRST_CHECK_MS - CHECK_PERIOD_MS;
int nextValue = 1;

void setup() {
	Serial.begin(115200);
  Particle.publish("Neuton model loaded", "");
  Particle.publish("Model Size: ", String(neuton_model_size()));
  Particle.publish("RAM USAGE: ", String(neuton_model_ram_usage()));
  Particle.publish("Inputs counts: ", String(neuton_model_inputs_count()));
  Particle.publish("Outputs counts: ", String(neuton_model_outputs_count()));
  Particle.publish("Neurons count: ", String(neuton_model_neurons_count()));
  Particle.publish("Weights count: ", String(neuton_model_weights_count()));
  
	Particle.subscribe("hook-response/diabetes-get", getDataHandler, MY_DEVICES);
}

void loop() {
	if (millis() - lastPublish >= CHECK_PERIOD_MS) {
		lastPublish = millis();

		Particle.publish(CHECK_EVENT_NAME, "", PRIVATE);
	}
}

void getDataHandler(const char *topic, const char *data)
{  
  StaticJsonDocument<256> doc;

  payload = data;
  payload.replace("\\""", "");
  payload.replace("\"\"", "\"");  
  payload.trim();
  
  snprintf(text, sizeof(text)-1, payload.c_str());
  //strcpy(text, (const char*)payload);
  // Serial.println(text);  

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, text);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }
  else
  {
    Serial.println(F("deserializeJson() succeeded."));

    // Get the value of the element in the document, in exact same order we used while crating neuton model.
    inputs[0] = atof(doc["preg"]);
    inputs[1] = atof(doc["glucose"]);
    inputs[2] = atof(doc["bp"]);
    inputs[3] = atof(doc["skin"]);
    inputs[4] = atof(doc["insulin"]);
    inputs[5] = atof(doc["bmi"]);
    inputs[6] = atof(doc["dpf"]);
    inputs[7] = atof(doc["age"]);

    if (neuton_model_set_inputs(inputs) == 0)
    {
        uint16_t index;
        float* outputs;

        start = millis();        
        if (neuton_model_run_inference(&index, &outputs) == 0)
        {
            stop = millis();
            inference_time = stop - start;

            Particle.publish("Inference time (ms): ", String(inference_time));
            // code for handling prediction result
            Serial.println("Prediction result:");
            Serial.println(index);
            delay(2000);
            Particle.publish("Prediction result: ", index==1?"diabetes yes":"diabetes no");

            // publish the output to the firebase integration
            publishPredictionData(index, inference_time, outputs);
        }
    }
  }  
}

void publishPredictionData(uint16_t index, unsigned long inference_time, float* outputs) 
{
	
	snprintf(text, sizeof(text), "{\"prediction\":%d,\"inferencetime\":%lu,\"confidence\":%.2f}", index, inference_time, outputs[index]);
	Serial.printlnf("publishing %s", text);
	Particle.publish(PUBLISH_EVENT_NAME, text, PRIVATE);
}