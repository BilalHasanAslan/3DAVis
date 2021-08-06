import asyncio
import websockets

async def hello():
    url = "ws://localhost:9000"
    
    try:
        websocket = await websockets.connect(url, ping_interval = None)
    except:
        print("fail")
        exit(0)
    msg = input("Message: ")
    await websocket.send(msg)
    message = await websocket.recv()
    print (message)
    
asyncio.get_event_loop().run_until_complete(hello())