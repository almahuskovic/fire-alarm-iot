#ifndef FIREBASE_HTTP_CLIENT_H
#define FIREBASE_HTTP_CLIENT_H

#include <string>

#include "Arduino.h"
#include "Stream.h"

struct HttpStatus {
  static const int TEMPORARY_REDIRECT = 307;
};

class FirebaseHttpClient {
 public:
  static FirebaseHttpClient* create();

  virtual void setReuseConnection(bool reuse) = 0;
  virtual void begin(const std::string& url) = 0;
  virtual void begin(const std::string& host, const std::string& path) = 0;

  virtual void end() = 0;

  virtual void addHeader(const std::string& name, const std::string& value) = 0;
  virtual void collectHeaders(const char* header_keys[],
                              const int header_key_count) = 0;
  virtual std::string header(const std::string& name) = 0;

  virtual int sendRequest(const std::string& method, const std::string& data) = 0;

  virtual std::string getString() = 0;

  virtual Stream* getStreamPtr() = 0;

  virtual std::string errorToString(int error_code) = 0;

  virtual bool connected() = 0;

 protected:
  static const uint16_t kFirebasePort = 443;
};

static const char kFirebaseFingerprint[] =
//"28:74:98:93:D7:0B:B3:96:68:2E:AC:3B:3A:45:F1:73:9F:35:3C:47";
//      "49:E0:54:6C:F8:C0:CC:79:CF:5C:5E:87:17:59:FE:FA:E2:86:FC:3E"; // 2020-02
"54:11:BF:7D:0C:82:E0:9C:C7:B2:F5:74:29:D5:91:B5:10:1B:30:DE";
#endif  // FIREBASE_HTTP_CLIENT_H
