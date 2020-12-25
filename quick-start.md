---
layout: default
title: Quick Start
---

C++ Requests is a [Python Requests](https://github.com/psf/requests) like library for sending HTTP requests. The library is inspired a lot by the [Cpr](https://github.com/whoshuu/cpr) project, yet uses Boost instead of cURL. We aim for most simple workflow with both HTTP and HTTPS protocols.

Sending a `GET` request is nothing more than:
{% raw %}
```c++
#include <requests/requests.hpp>

int main()
{
  Requests::Response r = Requests::get("https://api.github.com/user", Requests::Auth{"user", "pass"});

  r.status_code;             // 200
  r.headers["content-type"]; // "application/json; charset=utf8"
  r.text;                    // "{\"type\":\"User\"..."

  return 0;
}
```
{% endraw %}

## Features

C++ Requests currently supports:

* GET request
* POST request 
* PUT request 
* DELETE request 
* PATCH request 
* HEAD request 
* OPTIONS request
* HTTPS requests with OpenSSL
* Basic authentication

## Planned

The following features will be added in next releases:

* Asynchronous requests
* Cookies
* Timeouts
* Json
* Automatic dependencies installation
* CMake FetchContent and find_package support

And more!

## Dependencies

Requests deliberately uses most modern `C++20` features, hence it requires lastest versions of compilers.

It also requires:
- `Boost`
- `OpenSSL`

## Install

0. Install dependencies
```
sudo apt-get install libboost-dev openssl
```

1. Download sources
```
git clone https://github.com/gavrilikhin-d/requests
```

2. Build project
```
mkdir build
cd build
cmake ..
cmake --build .
```

3. Install
```
cmake --install .
```

## Contributing
Please fork this repository and contribute back using [pull requests](https://github.com/gavrilikhin-d/requests/pulls). Features can be requested using [issues](https://github.com/gavrilikhin-d/requests/issues). All code, comments, and critiques are greatly appreciated.
