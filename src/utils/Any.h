/**
 * rt-data
 * Copyright (C) 2019 Guillem Castro
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//Fordward declaration
template <typename T>
class AnyImpl;

/**
 * A class that can hold any value.
 * Do not create directly. It's better
 *  to use the utility function Any::create_any()
 */
class Any {

public:
    
    virtual ~Any() {}
    
    /**
     * Get the value hold by this object
     * @returns The value hold by the object
     */
    template<typename T>
    const T& get() const {
        return dynamic_cast<const AnyImpl<T>&>(*this).get();
    }

    /**
     * Set the value that this class will hold
     * @param content The content that this class will hold
     */
    template<typename T, typename U>
    void set(const U& content) {
        return dynamic_cast<AnyImpl<T>&>(*this).set(content);
    }

    /**
     * Set the value that this class will hold
     * @param content The content that this class will hold
     */
    template<typename T, typename U>
    void operator=(const U& content) {
        set(content);
    }

    /**
     * Create a smart pointer to a Any object that holds a content
     * @param content The content that will hold the created Any object
     */
    template<typename T>
    static std::shared_ptr<Any> create_any(const T& content) {
        return std::make_shared<AnyImpl<T>>(content);
    }

};

/**
 * Concrete implementation of Any.
 */
template <typename T>
class AnyImpl : public Any {

public:
    
    AnyImpl(const T& content) : content(content) {

    }
    
    const T& get() const {
        return content;
    }
    
    void set(const T& content) {
        this->content = content;
    }    

private:

    T content;

};