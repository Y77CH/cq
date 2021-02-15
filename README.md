# cq == C++ Requests

[![Documentation](https://img.shields.io/badge/docs-online-informational?label=Docs&style=flat&link=https://y77ch.github.io/cq/)](https://y77ch.github.io/cq/)
[![License](https://img.shields.io/github/license/Y77CH/cq?label=License)](https://github.com/Y77CH/cq/blob/master/LICENSE)

`cq == C++ Requests` is a ["Python Requests"](https://github.com/psf/requests)-like C++ header-only library for sending HTTP requests. The library is inspired a lot by the [Cpr](https://github.com/whoshuu/cpr) project, yet tries to be even more simple.

Sending a `GET` request is nothing more than:

```c++
#include "requests.hpp"

int main()
{
  auto r = requests::get("https://api.github.com/user", requests::auth{"user", "pass"});

  r.status_code;             // 200
  r.headers["content-type"]; // "application/json; charset=utf8"
  r.text;                    // "{\"type\":\"User\"..."

  return 0;
}
```

## Documentation

Documentation can be found [here](https://y77ch.github.io/cq/). Work in progress.

## Dependencies

- `cURL`
- Compiler that supports `C++20`

## Contributing

Please fork this repository and contribute back using [pull requests](https://github.com/Y77CH/cq/pulls). Features can be requested using [issues](https://github.com/Y77CH/cq/issues). All code, comments, and critiques are greatly appreciated.
