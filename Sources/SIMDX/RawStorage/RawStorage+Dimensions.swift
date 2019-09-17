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

// MARK: Dimensions

/// A storage type of exactly 2 values
public protocol RawStorage2: RawStorage {

    /// Initialize a raw SIMD storage to specified elements.
    init(_ index0: Element, _ index1: Element)
}

/// A storage type of exactly 3 values
public protocol RawStorage3: RawStorage {

    /// Initialize a raw SIMD storage to specified elements.
    init(_ index0: Element, _ index1: Element, _ index2: Element)
}

/// A storage type of exactly 4 values
public protocol RawStorage4: RawStorage {

    /// Initialize a raw SIMD storage to specified elements.
    init(_ index0: Element, _ index1: Element, _ index2: Element, _ index3: Element)
}

/// A storage type of exactly 5 values
public protocol RawStorage5: RawStorage {

    /// Initialize a raw SIMD storage to specified elements.
    init(_ index0: Element, _ index1: Element, _ index2: Element, _ index3: Element,
         _ index4: Element)
}

/// A storage type of exactly 6 values
public protocol RawStorage6: RawStorage {

    /// Initialize a raw SIMD storage to specified elements.
    init(_ index0: Element, _ index1: Element, _ index2: Element, _ index3: Element,
         _ index4: Element, _ index5: Element)
}

/// A storage type of exactly 7 values
public protocol RawStorage7: RawStorage {

    /// Initialize a raw SIMD storage to specified elements.
    init(_ index0: Element, _ index1: Element, _ index2: Element, _ index3: Element,
         _ index4: Element, _ index5: Element, _ index6: Element)
}

/// A storage type of exactly 8 values
public protocol RawStorage8: RawStorage {

    /// Initialize a raw SIMD storage to specified elements.
    init(_ index0: Element, _ index1: Element, _ index2: Element, _ index3: Element,
         _ index4: Element, _ index5: Element, _ index6: Element, _ index7: Element)
}

// MARK: Storables

/// A type that is representable in a storage of 2 values
public protocol RawStorable2 where Storage2.Element == Self {
    associatedtype Storage2: RawStorage2
}

/// A type that is representable in a storage of 3 values
public protocol RawStorable3 where Storage3.Element == Self {
    associatedtype Storage3: RawStorage3
}

/// A type that is representable in a storage of 4 values
public protocol RawStorable4 where Storage4.Element == Self {
    associatedtype Storage4: RawStorage4
}

/// A type that is representable in a storage of 5 values
public protocol RawStorable5 where Storage5.Element == Self {
    associatedtype Storage5: RawStorage5
}

/// A type that is representable in a storage of 6 values
public protocol RawStorable6 where Storage6.Element == Self {
    associatedtype Storage6: RawStorage6
}

/// A type that is representable in a storage of 7 values
public protocol RawStorable7 where Storage7.Element == Self {
    associatedtype Storage7: RawStorage7
}

/// A type that is representable in a storage of 8 values
public protocol RawStorable8 where Storage8.Element == Self {
    associatedtype Storage8: RawStorage8
}
