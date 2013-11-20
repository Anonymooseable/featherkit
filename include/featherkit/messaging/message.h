#pragma once
#include <tuple>


namespace fea
{
    template<class tag, typename... DataTypes>
    struct Message
    {
        Message(typename std::enable_if<sizeof...(DataTypes) >= 1>) {}
        Message(DataTypes... d) : data(d...) { }
        Message(const std::tuple<DataTypes...>& d) : data(d) { }
        std::tuple<DataTypes...> data;
        bool isLocal = true;
        bool onlyLocal = false;
    };
    /** @addtogroup Messaging
     *@{
     *  @struct Message
     *@}
     ***
     *  @struct Message
     *  @brief Message holding data.
     *
     *  Data container class to be used with the messaging system. Can hold any type of data. The types of the data it stores is defined using variadic template arguments. In other words, any amount of template arguments can be used. Here is an example of how a window resized message could be defined.
     *  @code
     *  //ResizedMessage definition. 
     *  //Sent when the window is resized, contains the dimensions of the new window size.
     *  //Data:
     *  //uint32_t - Width of the new size.
     *  //uint32_t - Height of the new size.
     *  struct Resized_tag{};
     *  using ResizedMessage = Message<Resized_tag, uint32_t, uint32_t>;
     *  using ResizedData = std::tuple<uint32_t, uint32_t>;
     *  @endcode
     *  The empty struct Resized_tag serves as a way of making this Message type unique. The using statements are useful for creating aliases that are easy to work with.
     ***
     *  @fn Message::Message(typename std::enable_if<sizeof...(DataTypes) >= 1>)
     *  @brief Construct a message.
     ***
     *  @fn Message::Message(DataTypes... d)
     *  @brief Construct a message containing the given data.
     *  @param d Data.
     ***
     *  @var Message::data 
     *  @brief Packed tuple of all data the Message is carrying.
     ***
     * @var Message::isLocal
     * @brief bool if the message has been created locally, or if it's sent from a server.
     ***
     * @var Message::onlyLocal
     * @brief whether or not the message should be sent to the server or not.
     **/
}
