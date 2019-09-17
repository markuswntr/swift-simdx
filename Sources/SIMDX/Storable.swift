// Copyright 2019 Markus Winter
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

import Foundation
import CSIMDX

extension Int32: RawStorable2, RawStorable3, RawStorable4 {
    public typealias Storage2 = Int32x2
    public typealias Storage3 = Int32x3
    public typealias Storage4 = Int32x4
}
extension Int64: RawStorable2/*, RawStorable3, RawStorable4*/ {
    public typealias Storage2 = Int64x2
//    public typealias Storage3 = Int64x3
//    public typealias Storage4 = Int64x4
}

extension UInt32: RawStorable2, RawStorable3, RawStorable4 {
    public typealias Storage2 = UInt32x2
    public typealias Storage3 = UInt32x3
    public typealias Storage4 = UInt32x4
}
extension UInt64: RawStorable2/*, RawStorable3, RawStorable4*/ {
    public typealias Storage2 = UInt64x2
//    public typealias Storage3 = UInt64x3
//    public typealias Storage4 = UInt64x4
}

extension Float32: RawStorable2, RawStorable3, RawStorable4 {
    public typealias Storage2 = Float32x2
    public typealias Storage3 = Float32x3
    public typealias Storage4 = Float32x4
}
extension Float64: RawStorable2/*, RawStorable3, RawStorable4*/ {
    public typealias Storage2 = Float64x2
//    public typealias Storage3 = Float64x3
//    public typealias Storage4 = Float64x4
}
