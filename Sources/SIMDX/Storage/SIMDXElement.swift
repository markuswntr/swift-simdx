// Copyright 2019-2022 Markus Winter
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

/// A type that can be stored in a SIMD2 lane.
///
/// Types conforming to this protocol can represent a single element of an SIMD
/// storage, where the SIMD storage can hold 2 (equal type) elements in total.
public protocol SIMDX2Element {
  associatedtype Storage2: SIMDX2Storage where Storage2.Element == Self
}

/// A type that can be stored in a SIMD3 lane.
///
/// Types conforming to this protocol can represent a single element of an SIMD
/// storage, where the SIMD storage can hold 3 (equal type) elements in total.
public protocol SIMDX3Element {
  associatedtype Storage3: SIMDX3Storage where Storage3.Element == Self
}

/// A type that can be stored in a SIMD4 lane.
///
/// Types conforming to this protocol can represent a single element of an SIMD
/// storage, where the SIMD storage can hold 4 (equal type) elements in total.
public protocol SIMDX4Element {
  associatedtype Storage4: SIMDX4Storage where Storage4.Element == Self
}

// MARK: - Implementations

extension Float32: SIMDX2Element, SIMDX3Element, SIMDX4Element {
  public typealias Storage2 = Float32x2
  public typealias Storage3 = Float32x3
  public typealias Storage4 = Float32x4
}

extension Float64: SIMDX2Element, SIMDX3Element, SIMDX4Element {
  public typealias Storage2 = Float64x2
  public typealias Storage3 = Float64x3
  public typealias Storage4 = Float64x4
}

//extension Int32: SIMDX2Element, SIMDX3Element, SIMDX4Element {
//    public typealias Storage2 = Int32x2
//    public typealias Storage3 = Int32x3
//    public typealias Storage4 = Int32x4
//}

//extension Int64: SIMDX2Element/* CSIMDX3Element, SIMDX4Element*/ {
//    public typealias Storage2 = Int64x2
//    public typealias Storage3 = Int64x3
//    public typealias Storage4 = Int64x4
//}

//extension UInt32: SIMDX2Element, SIMDX3Element, SIMDX4Element {
//    public typealias Storage2 = UInt32x2
//    public typealias Storage3 = UInt32x3
//    public typealias Storage4 = UInt32x4
//}

//extension UInt64: SIMDX2Element/* CSIMDX3Element, SIMDX4Element*/ {
//    public typealias Storage2 = UInt64x2
//    public typealias Storage3 = UInt64x3
//    public typealias Storage4 = UInt64x4
//}
