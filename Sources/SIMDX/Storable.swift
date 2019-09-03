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
