# Defaults for every CMake project configured inside this Pixi environment.
# CMAKE_TOOLCHAIN_FILE is read by CMake when configuring a new build tree.
if(DEFINED ENV{CONDA_PREFIX})
  list(PREPEND CMAKE_PREFIX_PATH "$ENV{CONDA_PREFIX}")
  set(HDF5_ROOT "$ENV{CONDA_PREFIX}" CACHE PATH "HDF5 from the active Pixi environment")
  set(HDF5_NO_FIND_PACKAGE_CONFIG_FILE ON CACHE BOOL "Avoid unrelated host HDF5 config files")
endif()
