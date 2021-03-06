#pragma once
#include <fea/config.hpp>
#include <tuple>

#define FEA_DECLARE_MESSAGE(name, ...)                      \
struct name##_tag{};                                 \
using name = fea::Message< name##_tag, ##__VA_ARGS__>;\
using name##Receiver = fea::MessageReceiver< name >;

namespace fea
{
    template<class tag, typename... DataTypes>
    struct FEA_API Message
    {
        Message();
        Message(DataTypes... data);
        Message(const std::tuple<DataTypes...>& data);
        std::tuple<DataTypes...> mData;
    };

#include <fea/messaging/message.inl>

    template<class tag>
    struct FEA_API Message<tag>
    {
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
     *  using ResizedMessageReceiver = MessageReceiver<ResizedMessage>;
     *  @endcode
     *  The empty struct Resized_tag serves as a way of making this Message type unique. The using statements are useful for creating aliases that are easy to work with.
     *
     *  There is also a macro which eases the process of creating a message. Expanded, it does the exact thing as above, but the only thing needed to be typed is:
     *  @code
     *  FEA_DECLARE_MESSAGE(ResizedMessage, uint32_t, uint32_t);
     *  @endcode
     ***
     *  @fn Message::Message()
     *  @brief Construct a message.
     ***
     *  @fn Message::Message(DataTypes... data)
     *  @brief Construct a message containing the given data.
     *  @param data Data.
     ***
     *  @fn Message::Message(const std::tuple<DataTypes...>& data)
     *  @brief Construct a message from a ready packed tuple.
     *  @param data Tuple.
     ***
     *  @var Message::mData 
     *  @brief Packed tuple of all data the Message is carrying.
     **/
}
