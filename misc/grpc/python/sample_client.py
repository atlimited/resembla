#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Resembla: Word-based Japanese similar sentence search library
# https://github.com/tuem/resembla
#
# Copyright 2017 Takashi Uemura
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import resembla_pb2

import sys
import grpc

_TIMEOUT_SECONDS = 10

def run(port, queries):
  channel = grpc.insecure_channel('localhost:' + str(port))
  resembla = resembla_pb2.ResemblaServiceStub(channel)

  for s in queries:
    print ('query=%s' % s)
    responses = resembla.find(resembla_pb2.ResemblaRequest(query=s), _TIMEOUT_SECONDS)
    for response in responses:
      print ('  response.text=%s' % response.text)
      print ('  response.score=%s' % response.score)
      print ('  response.replies:')

if __name__ == '__main__':
  if len(sys.argv) > 1:
    queries = sys.argv[1:]
  else:
    queries = ["りんごはおいしいよね", "りんごおいしくねえ", "りんごまずいから好きじゃない"]

  run(50051, queries)
