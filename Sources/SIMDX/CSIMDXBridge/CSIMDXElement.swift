// Copyright 2022 Markus Winter
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

import CSIMDX

// MARK: - Cardinality

/// A type that is representable in a SIMD register type of 2 values
public protocol CSIMDX2Element where RegisterType2.Element == Self {
  associatedtype RegisterType2: CSIMDX2
}

/// A type that is representable in a SIMD register type of 3 values
public protocol CSIMDX3Element where RegisterType3.Element == Self {
  associatedtype RegisterType3: CSIMDX3
}

/// A type that is representable in a SIMD register type of 4 values
public protocol CSIMDX4Element where RegisterType4.Element == Self {
  associatedtype RegisterType4: CSIMDX4
}

// MARK: - Implementations

//extension Int32: RawStorable2, RawStorable3, RawStorable4 {
//    public typealias Storage2 = Int32x2
//    public typealias Storage3 = Int32x3
//    public typealias Storage4 = Int32x4
//}
//extension Int64: RawStorable2/*, RawStorable3, RawStorable4*/ {
//    public typealias Storage2 = Int64x2
////    public typealias Storage3 = Int64x3
////    public typealias Storage4 = Int64x4
//}
//
//extension UInt32: RawStorable2, RawStorable3, RawStorable4 {
//    public typealias Storage2 = UInt32x2
//    public typealias Storage3 = UInt32x3
//    public typealias Storage4 = UInt32x4
//}
//extension UInt64: RawStorable2/*, RawStorable3, RawStorable4*/ {
//    public typealias Storage2 = UInt64x2
////    public typealias Storage3 = UInt64x3
////    public typealias Storage4 = UInt64x4
//}

extension Float32: CSIMDX2Element/*, RawStorable3, RawStorable4*/ {
  public typealias RegisterType2 = CFloat32x2
//    public typealias Storage3 = Float32x3
//    public typealias Storage4 = Float32x4
}
//extension Float64: RawStorable2/*, RawStorable3, RawStorable4*/ {
//    public typealias Storage2 = Float64x2
////    public typealias Storage3 = Float64x3
////    public typealias Storage4 = Float64x4
//}
