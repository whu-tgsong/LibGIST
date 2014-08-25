#ifndef TRAITS_HPP
#define TRAITS_HPP

#include <iterator>
#include <type_traits>
#include "clany_macros.h"

_CLANY_BEGIN
#define CHECK_TYPE(T1, T2, msg) static_assert(is_same<typename remove_constref<T1>::type, \
                                                      typename remove_constref<T2>::type>::value, #msg)

template<typename T>
struct remove_constref
{
    using type = typename remove_const<typename remove_reference<T>::type>::type;
};

//////////////////////////////////////////////////////////////////////////
// Iterator traits
template<typename T, typename = void>
struct is_iterator : false_type
{};

template<typename T>
struct is_iterator<T, typename enable_if<!is_same<typename T::iterator_category, void>::value>::type> : true_type
{};

template<typename T>
struct is_iterator<T*, void> : true_type
{};

template <typename Iterator, bool = is_iterator<Iterator>::value>
struct IteratorTraits
{};

template <typename Iterator>
struct IteratorTraits<Iterator, true>
{
    using value_type        = typename iterator_traits<Iterator>::value_type;
    using pointer           = typename iterator_traits<Iterator>::pointer;
    using reference         = typename iterator_traits<Iterator>::reference;
    using iterator_category = typename iterator_traits<Iterator>::iterator_category;
    using difference_type   = typename iterator_traits<Iterator>::difference_type;
};

template <typename Iterator>
struct iterator_value
{
    using type = typename IteratorTraits<Iterator>::value_type;
};

template <typename Iterator>
struct iterator_reference
{
    using type = typename IteratorTraits<Iterator>::reference;
};

template <typename Iterator>
struct iterator_pointer
{
    using type = typename IteratorTraits<Iterator>::pointer;
};

template <typename Iterator>
struct iterator_difference
{
    using type = typename IteratorTraits<Iterator>::difference_type;
};

template <typename Iterator>
struct iterator_category
{
    using type = typename IteratorTraits<Iterator>::iterator_category;
};

template<typename T, bool = is_iterator<T>::value>
struct is_const_iterator : false_type
{};

template<typename T>
struct is_const_iterator<T, true> : integral_constant<bool, is_const<typename remove_reference<decltype(*declval<T>())>::type>::value>
{};

template<typename T, bool = is_iterator<T>::value>
struct is_input_iterator : false_type
{};

template<typename T>
struct is_input_iterator<T, true> : integral_constant<bool, is_base_of<input_iterator_tag, typename iterator_category<T>::type>::value>
{};

template<typename T, bool = is_iterator<T>::value && !is_const_iterator<T>::value>
struct is_output_iterator : false_type
{};

template<typename T>
struct is_output_iterator<T, true> : integral_constant<bool, is_same<output_iterator_tag,        typename iterator_category<T>::type>::value ||
                                                             is_same<forward_iterator_tag,       typename iterator_category<T>::type>::value ||
                                                             is_same<bidirectional_iterator_tag, typename iterator_category<T>::type>::value ||
                                                             is_same<random_access_iterator_tag, typename iterator_category<T>::type>::value>
{};

template<typename T, bool = is_iterator<T>::value>
struct is_forward_iterator : false_type
{};

template<typename T>
struct is_forward_iterator<T, true> : integral_constant<bool, is_base_of<forward_iterator_tag, typename iterator_category<T>::type>::value>
{};

template<typename T, bool = is_iterator<T>::value>
struct is_bidirectional_iterator : false_type
{};

template<typename T>
struct is_bidirectional_iterator<T, true> : integral_constant<bool, is_base_of<bidirectional_iterator_tag, typename iterator_category<T>::type>::value>
{};

template<typename T, bool = is_iterator<T>::value>
struct is_random_access_iterator : false_type
{};

template<typename T>
struct is_random_access_iterator<T, true> : integral_constant<bool, is_base_of<random_access_iterator_tag, typename iterator_category<T>::type>::value>
{};
_CLANY_END

#endif // TRAITS_HPP