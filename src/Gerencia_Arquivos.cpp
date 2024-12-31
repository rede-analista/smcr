#include "include.h"
#include "globals.h"

/*
 * filesystem code - local and via webserver
*/

void handleFileSysFormat(AsyncWebServerRequest *request) {
  FILESYS.format();
  request->send(200, "text/json", "format complete");
}

String getContentType(String filename, AsyncWebServerRequest *request){
  if(request->hasArg("download")) return "application/octet-stream";
  else if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

void handleFileDownload(AsyncWebServerRequest *request) {
    if (!request->hasArg("file")) {
        request->send(400, "text/plain", "Arquivo não especificado");
        return;
    }
    String path = request->arg("file");
    Serial.printf_P(PSTR("handleFileDownload: '%s'\r\n"), path.c_str());
    if (!FILESYS.exists(path)) {
        request->send(404, "text/plain", "Arquivo não encontrado");
        return;
    }
    File file = FILESYS.open(path, "r");
    request->send(file, path, getContentType(path, request));
    file.close();
}

bool handleFileRead(String path, AsyncWebServerRequest *request){
  Serial.printf_P(PSTR("handleFileRead: %s\r\n"), path.c_str());
  if(path.endsWith("/")) path += "";
  String contentType = getContentType(path, request);
  String pathWithGz = path + ".gz";
  if(FILESYS.exists(pathWithGz) || FILESYS.exists(path))
  {
    if(FILESYS.exists(pathWithGz))
      path += ".gz";
    File file = FILESYS.open(path, "r");
    request->send(file, path, contentType);
    file.close();
   fV_imprimeSerial(3,"Read OK");
    return true;
  }
  Serial.printf("Read failed '%s', type '%s'\n", path.c_str(), contentType.c_str());
  return false;
}

void handleFileUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
    if(index == 0) {
        Serial.printf_P(PSTR("Iniciando upload de arquivo: %s\r\n"), filename.c_str());
        if(!filename.startsWith("/")) filename = "/" + filename;
        vF_arquivoUpload = FILESYS.open(filename, "w");
        if (!vF_arquivoUpload) {
            Serial.printf_P(PSTR("Falha ao abrir arquivo: %s\r\n"), filename.c_str());
        }
    }
  
    if(len) {
        if (vF_arquivoUpload) {
            vF_arquivoUpload.write(data, len);
            Serial.printf_P(PSTR("Gravando dados: %zu bytes\r\n"), len);
        } else {
           fV_imprimeSerial(3,"Arquivo não está aberto para gravação.");
        }
    }

    if(final) {
        if(vF_arquivoUpload) {
            vF_arquivoUpload.close();
            Serial.printf_P(PSTR("Upload concluído. Tamanho do arquivo: %d bytes\r\n"), index + len);
            sprintf(aC_bufferTemp, "File upload [%s] OK\n", filename.c_str());
            aS_Variaveis[26] += aC_bufferTemp;
        } else {
           fV_imprimeSerial(3,"Arquivo não foi fechado corretamente.");
        }
    }
}


void handleFileDelete(AsyncWebServerRequest *request) {
    if (!request->hasArg("file")) {
        request->send(500, "text/html", "<meta http-equiv='refresh' content='1;url=/main'>Bad arguments. <a href=/main>Back to list</a>");
        return;
    }
    String path = request->arg("file");
    Serial.printf_P(PSTR("handleFileDelete: '%s'\r\n"), path.c_str());
    if (path == "/") {
        request->send(500, "text/html", "<meta http-equiv='refresh' content='1;url=/main'>Can't delete root directory. <a href=/main>Back to list</a>");
        return;
    }
    if (!FILESYS.exists(path)) {
        request->send(200, "text/html", "<meta http-equiv='refresh' content='1;url=/main'>File not found. <a href=/main>Back to list</a>");
        return;
    }
    FILESYS.remove(path);
    request->send(200, "text/html", "<meta http-equiv='refresh' content='1;url=/main'>File deleted. <a href=/main>Back to list</a>");
    aS_Variaveis[26] += "Deleted " + path + "\n";
}


void handleFileCreate(AsyncWebServerRequest *request){
  if(!request->hasArg("file")) {
    request->send(500, "text/plain", "BAD ARGS");
    return;
  }
  String path = request->arg("file");
  Serial.printf_P(PSTR("handleFileCreate: %s\r\n"), path.c_str());
  if(path == "/") {
    request->send(500, "text/plain", "BAD PATH");
    return;
  }
  if(FILESYS.exists(path)) {
    request->send(500, "text/plain", "FILE EXISTS");
    return;
  }
  if(!path.startsWith("/")) path = "/" + path;
  File file = FILESYS.open(path, "w");
  if(file) {
    file.close();
    request->send(200, "text/html", "<meta http-equiv='refresh' content='1;url=/main'>File created. <a href=/main>Back to list</a>");
    aS_Variaveis[26] += "Created " + path + "\n";
  } else {
    request->send(500, "text/plain", "CREATE FAILED");
  }
}
