#!/bin/bash

curl -i -H 'Authorization: token 94c334cee0b65ec83b511e5e708e7272a4e8bead' \
    -d '{ \
        "name": "ubushaev-gm", \
        "auto_init": false, \
        "private": false, \
        "gitignore_template": "nanoc" \
      }' \
    https://api.github.com/orgs/kit-cpp-course/repos