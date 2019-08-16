import Foundation
import CSIMDX

// MARK: - SIMD Scalar Types
//extension Int32: RawStorable2, RawStorable3, RawStorable4 {
//    public typealias Storage2 = Int32x4
//    public typealias Storage3 = SIMD3<Self>
//    public typealias Storage4 = SIMD4<Self>
//}
//extension UInt32: RawStorable2, RawStorable3, RawStorable4 {
//    public typealias Storage2 = SIMD2<Self>
//    public typealias Storage3 = SIMD3<Self>
//    public typealias Storage4 = SIMD4<Self>
//}
extension Float32: RawStorable2, RawStorable3, RawStorable4 {
    public typealias Storage2 = Float32x2
    public typealias Storage3 = Float32x3
    public typealias Storage4 = Float32x4
}
//extension Float64: RawStorable2, RawStorable3, RawStorable4 {
//    public typealias RawVector2 = SIMD2<Self>
//    public typealias RawVector3 = SIMD3<Self>
//    public typealias RawVector4 = SIMD4<Self>
//}
