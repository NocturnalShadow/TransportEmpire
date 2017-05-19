#pragma once

enum class Role {
    CUSTOMER,
    DRIVER,
    ADMIN
};

enum class Command {
    LOGIN,
    ADD_ROUTE,
    GET_ROUTE,
    GET_ROUTE_LIST
};

enum class ResponseCode {
    OK				= 200,
    BadRequest		= 400,
    Unauthorized	= 401,
    Forbidden		= 403,
    NotFound		= 404
};

