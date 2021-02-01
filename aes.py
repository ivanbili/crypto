from Crypto.Cipher import AES

def sxor(s1,s2):    
    # convert strings to a list of character pair tuples
    # go through each tuple, converting them to ASCII code (ord)
    # perform exclusive or on the ASCII code
    # then convert the result back to ASCII (chr)
    # merge the resulting array of characters as a string
    return ''.join(chr(ord(a) ^ ord(b)) for a,b in zip(s1,s2))

def CBC_decrypt(key,cyphertext):
    decipher = AES.new(key, AES.MODE_ECB)
    message = ''
    curr_token = cyphertext[:16]
    for i in range(16, len(cyphertext), 16):
        prev_token = curr_token
        curr_token = cyphertext[i:i+16]
        message += sxor(decipher.decrypt(curr_token), prev_token)
    return message

def CTR_decrypt(key,cyphertext):
    decipher = AES.new(key, AES.MODE_ECB)
    message = ''
    IV = int(cyphertext[:16].encode("hex"), 16)
    for i in range(16, len(cyphertext), 16):
        curr_token = cyphertext[i:i+16]
        message += sxor(decipher.encrypt(hex(IV)[2:][:32].decode("hex")), curr_token)
        IV += 1
    return message

key =    "140b41b22a29beb4061bda66b6747e14".decode("hex")
cypher = "4ca00ff4c898d61e1edbf1800618fb2828a226d160dad07883d04e008a7897ee2e4b7465d5290d0c0e6c6822236e1daafb94ffe0c5da05d9476be028ad7c1d81".decode("hex")
print(CBC_decrypt(key, cypher))
key =    "140b41b22a29beb4061bda66b6747e14".decode("hex")
cypher = "5b68629feb8606f9a6667670b75b38a5b4832d0f26e1ab7da33249de7d4afc48e713ac646ace36e872ad5fb8a512428a6e21364b0c374df45503473c5242a253".decode("hex")
print(CBC_decrypt(key, cypher))
key =    "36f18357be4dbd77f050515c73fcf9f2".decode("hex")
cypher = "69dda8455c7dd4254bf353b773304eec0ec7702330098ce7f7520d1cbbb20fc388d1b0adb5054dbd7370849dbf0b88d393f252e764f1f5f7ad97ef79d59ce29f5f51eeca32eabedd9afa9329".decode("hex")
print(CTR_decrypt(key, cypher))
key =    "36f18357be4dbd77f050515c73fcf9f2".decode("hex")
cypher = "770b80259ec33beb2561358a9f2dc617e46218c0a53cbeca695ae45faa8952aa0e311bde9d4e01726d3184c34451".decode("hex")
print(CTR_decrypt(key, cypher))
