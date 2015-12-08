# tryThreadedTcpSockets
C threads and sockets auto tutorial

## do it first

    make

## Threads
    ./ficheux    # example from a guy
    ./pesenti    # another example from another guy
    ./simpleSem  # try semaphores
    ./threadUser # other threads examples
   

## Sockets

monothread bidirectionnal communication

    ./tcpServer 1234
    # change term
    ./tcpClient localhost 1234

## Threaded Sockets
paralal threaded bidirectionnal communication

    ./threadedServer 1234
    # change term
    ./threadedClient localhost 1234

## Passing struct over tcp
one (simple) way to send C struct over network
(without serializing).

    ./frameServer 1234
    # change term
    ./frameClient localhost 1234
