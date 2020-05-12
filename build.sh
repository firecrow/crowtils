#!/bin/sh
cc=clang-9
package=$1
$cc -o "test_${package}" "test_${package}.c"
