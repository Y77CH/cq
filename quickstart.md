---
layout: default
title: Quickstart
---

# Quickstart

This page gives a good introduction in how to get started with Requests.

First, make sure that:
* Requests is installed
* Requests is up-to-date

Let’s get started with some simple examples.

## Make a Request

Making a request with Requests is as simple as in python.

Begin by importing the Requests module (while C++20 modules not fully supported including header instead):

{% raw %}
```c++
#include <requests/requests.hpp>
```
{% endraw %}

Now, let’s try to get a webpage. For this example, let’s get GitHub’s public timeline:

{% raw %}
```c++
auto r = Requests::get("https://api.github.com/events");
```
{% endraw %}

Now, we have a Requests::Response object called r. We can get all the information we need from this object.

### Request options

* Requests::Auth
* Requests::Data
* Requests::Fragment
* Requests::Header
* Requests::Headers
* Requests::Json
* Requests::Query
* Requests::Text
* Requests::Url
