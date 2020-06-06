#! /bin/sh
make && MESA_GL_VERSION_OVERRIDE=4.3 ./openglTest "$@"
