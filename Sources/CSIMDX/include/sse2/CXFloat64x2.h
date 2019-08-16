#pragma once

//public struct Float32x2: RawStorage2 {
//
//    // MARK: Collection Conformance
//
//    public let startIndex: Int32 = 0
//
//    public let endIndex: Int32 = 2
//
//    // MARK: Raw Value Access
//
//    @inline(__always)
//    public fileprivate(set) var rawValue: CXFloat32x2
//
//    @inline(__always)
//    public subscript(index: Int32) -> Float32 {
//        @inline(__always) set {
//            CXFloat32x2SetElement(&rawValue, index, newValue)
//        }
//        @inline(__always) get {
//            CXFloat32x2GetElement(rawValue, index)
//        }
//    }
//
//    @inline(__always)
//    public init(rawValue: CXFloat32x2) {
//        self.rawValue = rawValue
//    }
//}


//
//typedef __m128d SIMDX2Float64;
//inline SIMDX2Float64 InitSIMDX2Float64(double value0, int value1) {
//    return _mm_setr_pd(value0, value1);
//}
