#ifndef NEUTON_MODEL_MODEL_H
#define NEUTON_MODEL_MODEL_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Model info */
#define NEUTON_MODEL_HEADER_VERSION 3
#define NEUTON_MODEL_QLEVEL 32
#define NEUTON_MODEL_FLOAT_SUPPORT 1
#define NEUTON_MODEL_TASK_TYPE 1  // binary classification
#define NEUTON_MODEL_NEURONS_COUNT 6
#define NEUTON_MODEL_WEIGHTS_COUNT 29
#define NEUTON_MODEL_INPUTS_COUNT 8
#define NEUTON_MODEL_INPUT_LIMITS_COUNT 8
#define NEUTON_MODEL_OUTPUTS_COUNT 2
#define NEUTON_MODEL_LOG_SCALE_OUTPUTS 0
#define NEUTON_MODEL_HAS_CLASSES_RATIO 0
#define NEUTON_MODEL_HAS_NEGPOS_RATIO 0

/* Preprocessing */
#define NEUTON_PREPROCESSING_ENABLED 0
#define NEUTON_DROP_ORIGINAL_FEATURES 0
#define NEUTON_BITMASK_ENABLED 1
#define NEUTON_INPUTS_IS_INTEGER 0
#define NEUTON_MODEL_SA_PRECISION 24

/* Types */
typedef float input_t;
typedef float extracted_feature_t;
typedef float coeff_t;
typedef float weight_t;
typedef double acc_signed_t;
typedef double acc_unsigned_t;
typedef uint8_t sources_size_t;
typedef uint8_t weights_size_t;
typedef uint8_t neurons_size_t;

/* Limits */
static const input_t modelInputMin[] = { 0, 0, 0, 0, 0, 0, 0.078000002, 21 };
static const input_t modelInputMax[] = {
	14, 198, 122, 99, 846, 57.299999, 2.329, 81 };

static const uint8_t modelUsedInputsMask[] = { 0xff };

/* Structure */
static const weight_t modelWeights[] = {
	-0.16939661, -0.73885411, -0.0082673747, 0.18665278, -0.33041641, 0.48352814,
	0.5602113, 0.31170839, -0.64733255, -0.62513858, -0.10368107, -0.93836105,
	-0.021976763, -0.077091873, 0.25681368, -0.036867496, -0.06370616, -0.8568716,
	0.58698159, -0.064200141, 0.99277931, -0.8488633, 0.58405238, -0.0046515483,
	-0.015531139, -0.12017119, 0.73605269, -0.4812513, 0.22036411 };

static const sources_size_t modelLinks[] = {
	0, 1, 3, 4, 6, 8, 0, 2, 5, 7, 8, 0, 0, 2, 5, 7, 8, 1, 2, 8, 0, 1, 2, 1,
	2, 8, 0, 4, 8 };

static const weights_size_t modelIntLinksBoundaries[] = { 0, 7, 12, 19, 23, 28 };
static const weights_size_t modelExtLinksBoundaries[] = {
	6, 11, 17, 20, 26, 29 };

static const coeff_t modelFuncCoeffs[] = {
	19.738285, 10.747753, 30.024981, 4.9536371, 14.439027, 6.422267 };
static const uint8_t modelFuncTypes[] = { 0, 0, 0, 0, 0, 0 };

static const neurons_size_t modelOutputNeurons[] = { 5, 3 };

#ifdef __cplusplus
}
#endif

#endif // NEUTON_MODEL_MODEL_H

