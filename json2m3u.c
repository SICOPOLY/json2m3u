#include <stdio.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <CStdString.h>

typedef CStdString CString; //CstdStringA, CStdStringW, CStdStringO are also available
//using json = nlohmann::json; ///Ordena Alphabeticamente las insercciones automaticamente
using json = nlohmann::ordered_json; //Respeta el orden de insercion

//Prototipos



int main(int argc, char *argv[]) {
	int i = 0;
	int k = 0;
	CString sFileName;
	char sBuffer[1024] = "";
	char sTvGroup[80] = "";
	char sTvName[80] = "";
	char sTvImage[256] = "";
	char sTvUrl[512] = "";
	//char sTvUrl_1[512] = "";
	//char sTvUrl_2[512] = "";
	char sTvEpgId[80] = "";


	if (argc != 0) {
		sFileName = argv[1];
	} else {
		printf("argc=%d\n", argc);
	}

	if (sFileName.IsEmpty()) {
		printf("Falta que indiquese el fichero de entrada como parametro\n");
		printf("Ejemplo: ./HelloWorld tv.json\n");
		return -1;
	}

	std::ifstream inFile(sFileName.c_str(), std::ifstream::binary);
	json j;
	inFile >> j;

	std::ofstream outFile;

	sFileName.Replace("json", "m3u8");
	outFile.open(sFileName.c_str());

	if (j["epg"].is_null()) {
		sprintf(sBuffer, "#EXTM3U url-tvg=\"https://www.tdtchannels.com/epg/TV.xml\"\n");
	} else {
		if (j["epg"].get<std::string>().empty()) {
			sprintf(sBuffer, "#EXTM3U url-tvg=\"https://www.tdtchannels.com/epg/TV.xml\"\n");
		} else {
			sprintf(sBuffer, "#EXTM3U url-tvg=\"%s\"\n", j["epg"].get<std::string>().c_str());
		}
	}

	outFile.write(sBuffer, strlen(sBuffer));

	for (i = 0; i < j["groups"].size(); i++) {
		//printf("%s\n", j["groups"][i]["name"].get<std::string>().c_str());
		sprintf(sTvGroup, "%s", j["groups"][i]["name"].get<std::string>().c_str());
		for (k = 0; k < j["groups"][i]["stations"].size(); k++) {
			//printf("\t%s\n", j["groups"][i]["stations"][k]["name"].get<std::string>().c_str());
			sprintf(sTvName, "%s", j["groups"][i]["stations"][k]["name"].get<std::string>().c_str());
			sprintf(sTvImage, "%s", j["groups"][i]["stations"][k]["image"].get<std::string>().c_str());
			sprintf(sTvUrl, "%s", j["groups"][i]["stations"][k]["url"].get<std::string>().c_str());
			//sprintf(sTvUrl_1, "%s", j["groups"][i]["stations"][k]["url1"].get<std::string>().c_str());
			//sprintf(sTvUrl_2, "%s", j["groups"][i]["stations"][k]["url2"].get<std::string>().c_str());
			sprintf(sTvEpgId, "%s", j["groups"][i]["stations"][k]["epgId"].get<std::string>().c_str());

			sprintf(sBuffer, "#EXTINF:-1 tvg-id=\"%s\" tvg-log=\"%s\" group-title=\"%s\" tvg-name=\"%s\",%s\n%s\n", sTvEpgId, sTvImage, sTvGroup, sTvName, sTvName, sTvUrl);

			outFile.write(sBuffer, strlen(sBuffer));
		}
	}

	outFile.close();


	return 0;
}

