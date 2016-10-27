To build tests,

- Sync the gtest submodule:
`git submodule update --init --remote`

- Add -DBUILD_TEST to your cmake build.

- make

- Run motion_control_test