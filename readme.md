![logo img](img/logo.png)

---

### Stack

This project using 
* [C++17](https://en.cppreference.com/w/cpp/17)
* [nlohmann/json](https://github.com/nlohmann/json)
* [spdlog](https://github.com/gabime/spdlog)
* [gtest](https://github.com/google/googletest)

---

### Building

1. Clone this repository using `git`

```bash
git clone --recursive https://github.com/szmxnv/search_engine
```

2. Open downloaded repository 
```bash
cd search_engine
```

3. Create project files in project root directory using `cmake`
```bash
cmake -B build
```

4. Compile:
```bash
cmake --build build --config Release
```

---

### Using

1. Create config file with name `config.json` and requests file with name `requests.json`
2. Add this lines to the config.json:
    ```json
    {
        "config": 
        {
            "name": "search_engine",
            "version": "0.1",
            "max_responses": 5
        },
        "files": 
        [
            "your",
            "files",
            "here"
        ]
    }
    ```

    and add this to the requests.json:
    ```json
    {
        "requests": [
            "request here"
        ]
    }
    ```

    or use `--config` command
    ```bash
    search_engine --config
    ```

3. In config file add your file's path (relative or absolute path)
4. Run `search_engine` and wait for the results 