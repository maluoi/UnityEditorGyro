// Author: Nick Klingensmith - @koujaku (Twitter)
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma comment(lib, "sensorsapi.lib")
#pragma comment(lib, "PortableDeviceGuids.lib")

#include <InitGuid.h>
#include <SensorsApi.h>
#include <Sensors.h>

typedef struct {
	float x, y, z, w;
} Vector4;

ISensor        *sensor;
ISensorManager *sensorManager = 0;

extern "C" {
	__declspec(dllexport) HRESULT GyroInitialize();
	__declspec(dllexport) HRESULT GyroIsInitialized();
	__declspec(dllexport) Vector4 GyroGetRotation();

	HRESULT GyroInitialize() {
		HRESULT hr = 0;
		ISensorCollection* sensorCollection = NULL;

		CoInitializeEx(0, COINIT_APARTMENTTHREADED);
		hr = CoCreateInstance(CLSID_SensorManager, 0, CLSCTX_ALL, __uuidof(ISensorManager), (void**)&sensorManager);
		if (FAILED(hr)) return -1;

		hr = sensorManager->GetSensorsByType(SENSOR_TYPE_AGGREGATED_DEVICE_ORIENTATION, &sensorCollection);
		if (FAILED(hr)) return -2;

		hr = sensorCollection->GetAt(0, &sensor);
		if (FAILED(hr)) return -3;

		return 1;
	}
	HRESULT GyroIsInitialized()
	{
		return sensor != NULL ? 1 : -1;
	}
	Vector4 GyroGetRotation() {
		ISensorDataReport *report;
		HRESULT hr = 0;
		Vector4 result = { 0,0,0,0 };
		PROPVARIANT data;

		hr = sensor->GetData(&report);
		if (FAILED(hr)) { return result; }

		hr = report->GetSensorValue(SENSOR_DATA_TYPE_QUATERNION, &data);
		if (FAILED(hr)) { return result; }

		UINT   cElement = data.caub.cElems / sizeof(UINT);
		float* pElement = (float*)(data.caub.pElems);

		result.x = pElement[0];
		result.y = pElement[1];
		result.z = -pElement[2];
		result.w = -pElement[3];
		return result;
	}
}