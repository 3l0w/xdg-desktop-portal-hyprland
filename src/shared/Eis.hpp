#pragma once

#include <libeis.h>
#include <string>

/*
 * Responsible to creating a socket for input communication
 */
class EmulatedInputServer {
  public:
    EmulatedInputServer(std::string socketPath);
    std::string socketPath;

    void        startEmulating(int activationId);
    void        stopEmulating();

    void        sendMotion(double x, double y);
    void        sendKey(uint32_t key, bool pressed);
    void        sendButton(uint32_t button, bool pressed);
    void        sendScrollDelta(double x, double y);
    void        sendScrollDiscrete(int32_t x, int32_t y);
    void        sendScrollStop(bool stopX, bool stopY);
    void        sendPointerFrame();

    int         getFileDescriptor();

    void        stopServer();

  private:
    bool stop   = false;
    eis* eisCtx = nullptr;

    struct Client {
        eis_client* handle = nullptr;
        eis_seat*   seat   = nullptr;

        eis_device* pointer  = nullptr;
        eis_device* keyboard = nullptr;
    } client;

    int  onEvent(eis_event* e);
    void pollEvents();
    void ensurePointer(eis_event* event);
    void ensureKeyboard(eis_event* event);
    void clearPointer();
    void clearKeyboard();
};
