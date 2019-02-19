import rospy
from roboy_middleware_msgs.srv import OptigaSign, OptigaSignResponse
import numpy as np
from ecdsa import VerifyingKey
import hashlib
import ecdsa

rospy.init_node("optiga_verifier")
optiga_srv =rospy.ServiceProxy('optiga', OptigaSign)
x = np.zeros(128)

h = hashlib.sha256(x).digest()

res = OptigaSignResponse()
res = optiga_srv(h)


vk = VerifyingKey.from_pem(open("pubkey.pem").read())

if res.signature[2] == '\x00':
	res.signature = res.signature[:2] + res.signature[3:]

rr = res.signature[2:34]

if res.signature[36] == '\x00':
	res.signature = res.signature[:36] + res.signature[37:]

ss = res.signature[36:]

signature = rr + ss

vk.verify_digest(signature, h)

