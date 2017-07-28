# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: resembla.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='resembla.proto',
  package='resembla.server',
  syntax='proto3',
  serialized_pb=_b('\n\x0eresembla.proto\x12\x0fresembla.server\" \n\x0fResemblaRequest\x12\r\n\x05query\x18\x01 \x01(\t\"/\n\x10ResemblaResponse\x12\x0c\n\x04text\x18\x01 \x01(\t\x12\r\n\x05score\x18\x02 \x01(\x02\x32\x62\n\x0fResemblaService\x12O\n\x04\x66ind\x12 .resembla.server.ResemblaRequest\x1a!.resembla.server.ResemblaResponse\"\x00\x30\x01\x62\x06proto3')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_RESEMBLAREQUEST = _descriptor.Descriptor(
  name='ResemblaRequest',
  full_name='resembla.server.ResemblaRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='query', full_name='resembla.server.ResemblaRequest.query', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=35,
  serialized_end=67,
)


_RESEMBLARESPONSE = _descriptor.Descriptor(
  name='ResemblaResponse',
  full_name='resembla.server.ResemblaResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='text', full_name='resembla.server.ResemblaResponse.text', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='score', full_name='resembla.server.ResemblaResponse.score', index=1,
      number=2, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=69,
  serialized_end=116,
)

DESCRIPTOR.message_types_by_name['ResemblaRequest'] = _RESEMBLAREQUEST
DESCRIPTOR.message_types_by_name['ResemblaResponse'] = _RESEMBLARESPONSE

ResemblaRequest = _reflection.GeneratedProtocolMessageType('ResemblaRequest', (_message.Message,), dict(
  DESCRIPTOR = _RESEMBLAREQUEST,
  __module__ = 'resembla_pb2'
  # @@protoc_insertion_point(class_scope:resembla.server.ResemblaRequest)
  ))
_sym_db.RegisterMessage(ResemblaRequest)

ResemblaResponse = _reflection.GeneratedProtocolMessageType('ResemblaResponse', (_message.Message,), dict(
  DESCRIPTOR = _RESEMBLARESPONSE,
  __module__ = 'resembla_pb2'
  # @@protoc_insertion_point(class_scope:resembla.server.ResemblaResponse)
  ))
_sym_db.RegisterMessage(ResemblaResponse)


try:
  # THESE ELEMENTS WILL BE DEPRECATED.
  # Please use the generated *_pb2_grpc.py files instead.
  import grpc
  from grpc.framework.common import cardinality
  from grpc.framework.interfaces.face import utilities as face_utilities
  from grpc.beta import implementations as beta_implementations
  from grpc.beta import interfaces as beta_interfaces


  class ResemblaServiceStub(object):

    def __init__(self, channel):
      """Constructor.

      Args:
        channel: A grpc.Channel.
      """
      self.find = channel.unary_stream(
          '/resembla.server.ResemblaService/find',
          request_serializer=ResemblaRequest.SerializeToString,
          response_deserializer=ResemblaResponse.FromString,
          )


  class ResemblaServiceServicer(object):

    def find(self, request, context):
      context.set_code(grpc.StatusCode.UNIMPLEMENTED)
      context.set_details('Method not implemented!')
      raise NotImplementedError('Method not implemented!')


  def add_ResemblaServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
        'find': grpc.unary_stream_rpc_method_handler(
            servicer.find,
            request_deserializer=ResemblaRequest.FromString,
            response_serializer=ResemblaResponse.SerializeToString,
        ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
        'resembla.server.ResemblaService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))


  class BetaResemblaServiceServicer(object):
    """The Beta API is deprecated for 0.15.0 and later.

    It is recommended to use the GA API (classes and functions in this
    file not marked beta) for all further purposes. This class was generated
    only to ease transition from grpcio<0.15.0 to grpcio>=0.15.0."""
    def find(self, request, context):
      context.code(beta_interfaces.StatusCode.UNIMPLEMENTED)


  class BetaResemblaServiceStub(object):
    """The Beta API is deprecated for 0.15.0 and later.

    It is recommended to use the GA API (classes and functions in this
    file not marked beta) for all further purposes. This class was generated
    only to ease transition from grpcio<0.15.0 to grpcio>=0.15.0."""
    def find(self, request, timeout, metadata=None, with_call=False, protocol_options=None):
      raise NotImplementedError()


  def beta_create_ResemblaService_server(servicer, pool=None, pool_size=None, default_timeout=None, maximum_timeout=None):
    """The Beta API is deprecated for 0.15.0 and later.

    It is recommended to use the GA API (classes and functions in this
    file not marked beta) for all further purposes. This function was
    generated only to ease transition from grpcio<0.15.0 to grpcio>=0.15.0"""
    request_deserializers = {
      ('resembla.server.ResemblaService', 'find'): ResemblaRequest.FromString,
    }
    response_serializers = {
      ('resembla.server.ResemblaService', 'find'): ResemblaResponse.SerializeToString,
    }
    method_implementations = {
      ('resembla.server.ResemblaService', 'find'): face_utilities.unary_stream_inline(servicer.find),
    }
    server_options = beta_implementations.server_options(request_deserializers=request_deserializers, response_serializers=response_serializers, thread_pool=pool, thread_pool_size=pool_size, default_timeout=default_timeout, maximum_timeout=maximum_timeout)
    return beta_implementations.server(method_implementations, options=server_options)


  def beta_create_ResemblaService_stub(channel, host=None, metadata_transformer=None, pool=None, pool_size=None):
    """The Beta API is deprecated for 0.15.0 and later.

    It is recommended to use the GA API (classes and functions in this
    file not marked beta) for all further purposes. This function was
    generated only to ease transition from grpcio<0.15.0 to grpcio>=0.15.0"""
    request_serializers = {
      ('resembla.server.ResemblaService', 'find'): ResemblaRequest.SerializeToString,
    }
    response_deserializers = {
      ('resembla.server.ResemblaService', 'find'): ResemblaResponse.FromString,
    }
    cardinalities = {
      'find': cardinality.Cardinality.UNARY_STREAM,
    }
    stub_options = beta_implementations.stub_options(host=host, metadata_transformer=metadata_transformer, request_serializers=request_serializers, response_deserializers=response_deserializers, thread_pool=pool, thread_pool_size=pool_size)
    return beta_implementations.dynamic_stub(channel, 'resembla.server.ResemblaService', cardinalities, options=stub_options)
except ImportError:
  pass
# @@protoc_insertion_point(module_scope)
