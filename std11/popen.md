  # popen
  ## 1 Get No_block result
  ```cpp
  auto p = popen(cmd.c_str(), "r");
  int rc = fscanf(p, "%*s addr:%s", tmp_str);
  ```