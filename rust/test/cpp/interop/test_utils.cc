// Protocol Buffers - Google's data interchange format
// Copyright 2023 Google LLC.  All rights reserved.
// https://developers.google.com/protocol-buffers/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google LLC. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <cstddef>

#include "absl/strings/string_view.h"
#include "google/protobuf/rust/cpp_kernel/cpp_api.h"
#include "google/protobuf/unittest.pb.h"

extern "C" void MutateTestAllTypes(protobuf_unittest::TestAllTypes* msg) {
  msg->set_optional_int64(42);
  msg->set_optional_bytes("something mysterious");
  msg->set_optional_bool(false);
}

extern "C" google::protobuf::rust_internal::SerializedData SerializeTestAllTypes(
    const protobuf_unittest::TestAllTypes* msg) {
  return google::protobuf::rust_internal::SerializeMsg(msg);
}

extern "C" void* DeserializeTestAllTypes(const void* data, size_t size) {
  auto* proto = new protobuf_unittest::TestAllTypes;
  proto->ParseFromArray(data, size);
  return proto;
}

extern "C" void* NewWithExtension() {
  auto* proto = new protobuf_unittest::TestAllExtensions;
  proto->SetExtension(protobuf_unittest::optional_bytes_extension, "smuggled");
  return proto;
}

extern "C" google::protobuf::rust_internal::PtrAndLen GetBytesExtension(
    const protobuf_unittest::TestAllExtensions* proto) {
  absl::string_view bytes =
      proto->GetExtension(protobuf_unittest::optional_bytes_extension);
  return {bytes.data(), bytes.size()};
}
