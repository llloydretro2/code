/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_HW7CLIENT_H_
#define JSONRPC_CPP_STUB_HW7CLIENT_H_

#include <jsonrpccpp/client.h>

class hw7Client : public jsonrpc::Client
{
    public:
        hw7Client(jsonrpc::IClientConnector &conn, jsonrpc::clientVersion_t type = jsonrpc::JSONRPC_CLIENT_V2) : jsonrpc::Client(conn, type) {}

        Json::Value update(const std::string& updating_json) 
        {
            Json::Value p;
            p["updating_json"] = updating_json;
            Json::Value result = this->CallMethod("update",p);
            if (result.isObject())
                return result;
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
        Json::Value search(const std::string& search_clause) 
        {
            Json::Value p;
            p["search_clause"] = search_clause;
            Json::Value result = this->CallMethod("search",p);
            if (result.isObject())
                return result;
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
};

#endif //JSONRPC_CPP_STUB_HW7CLIENT_H_