#ifndef COMMON_H_
#define COMMON_H_

//#include <openssl/ssl.h>
//#include <openssl/x509.h>

class Common
{
public:
	static bool ValidateServerCertificate();
	//static bool ValidateServerCertificate(X509_STORE_CTX* ctx, void* param);
};

#endif			// COMMON_H_