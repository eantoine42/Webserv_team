#include "../../includes/response.hpp"

std::map<status_code_t, std::string> response::init_code_status()
{
			std::map<status_code_t, std::string> status;
			status[CONTINUE] = "Continue";
			status[SWITCHING_PROTOCOLS] = "Switching Protocols";
			status[OK] = "OK";
			status[CREATED] = "Created";
			status[ACCEPTED] = "Accepted";
			status[NON_AUTHORITATIVE_INFORMATION] = "Non-Authoritative Information";
			status[NO_CONTENT] = "No Content";
			status[RESET_CONTENT] = "Reset Content";
			status[PARTIAL_CONTENT] = "Partial Content";
			status[MULTIPLE_CHOICES] = "Multiple Choices";
			status[MOVED_PERMANENTLY] = "Moved Permanently";
			status[FOUND] = "Found";
			status[SEE_OTHER] = "See Other";
			status[NOT_MODIFIED] = "Not Modified";
			status[USE_PROXY] = "Use Proxy";
			status[TEMPORARY_REDIRECT] = "Temporary Redirect";
			status[BAD_REQUEST] = "Bad Request";
			status[UNAUTHORIZED] = "Unauthorized";
			status[PAYMENT_REQUIRED] = "Payment Required";
			status[FORBIDDEN] = "Forbidden";
			status[NOT_FOUND] = "Not Found";
			status[METHOD_NOT_ALLOWED] = "Method Not Allowed";
			status[NOT_ACCEPTABLE] = "Not Acceptable";
			status[PROXY_AUTHENTICATION_REQUIRED] = "Proxy Authentication Required";
			status[REQUEST_TIMEOUT] = "Request Timeout";
			status[CONFLICT] = "Conflict";
			status[GONE] = "Gone";
			status[LENGTH_REQUIRED] = "Length Required";
			status[PRECONDITION_FAILED] = "Precondition Failed";
			status[PAYLOAD_TOO_LARGE] = "Payload Too Large";
			status[URI_TOO_LONG] = "URI Too Long";
			status[UNSUPPORTED_MEDIA_TYPE] = "Unsupported Media Type";
			status[RANGE_NOT_SATISFIABLE] = "Range Not Satisfiable";
			status[EXPECTATION_FAILED] = "Expectation Failed";
			status[INTERNAL_SERVER_ERROR] = "Internal Server Error";
			status[NOT_IMPLEMENTED] = "Not Implemented";
			status[BAD_GATEWAY] = "Bad Gateway";
			status[SERVICE_UNAVAILABLE] = "Service Unavailable";
			status[GATEWAY_TIMEOUT] = "Gateway Timeout";
			status[HTTP_VERSION_NOT_SUPPORTED] = "HTTP Version Not Supported";

			return status;
		}
