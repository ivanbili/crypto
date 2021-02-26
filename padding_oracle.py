import urllib2
import sys
import binascii

TARGET = 'http://crypto-class.appspot.com/po?er='
#--------------------------------------------------------------
# padding oracle
#--------------------------------------------------------------
class PaddingOracle(object):
    def query(self, q):
        target = TARGET + urllib2.quote(q)    # Create query URL
        req = urllib2.Request(target)         # Send HTTP request to server
        try:
            f = urllib2.urlopen(req)          # Wait for response
        except urllib2.HTTPError, e:
            #print "We got: %d" % e.code       # Print response code
            if e.code == 404:
                return True # good padding
            return False # bad padding

    def attack(self, hex_str, index):
        bin_str=binascii.a2b_hex(hex_str)
        bin_list=[ord(x) for x in bin_str]
        for i in range(256):
            bin_list[index] = (bin_list[index]+1)%256
            char_list = [chr(x) for x in bin_list]
            char_str = "".join(char_list)
            new_hex_str = binascii.b2a_hex(char_str)
            if self.query(new_hex_str):
                return bin_list[index]

    def decode(self, iv_hex_str, data_hex_str):
        decoded_str = ""
        for i in reversed(range(16)):
            answer = self.attack(iv_hex_str+data_hex_str, i)
            iv_bin_str = binascii.a2b_hex(iv_hex_str)
            iv_bin_list = [ord(x) for x in iv_bin_str]
            text_char_bin = answer ^ (16-i) ^ iv_bin_list[i]
            decoded_str = decoded_str + chr(text_char_bin)
            for j in range(i+1, 16):
                iv_bin_list[j] = iv_bin_list[j] ^ (16-i) ^ (17-i)
            iv_bin_list[i] = iv_bin_list[i] ^ text_char_bin ^ (17-i)
            iv_char_list = [chr(x) for x in iv_bin_list]
            iv_str = "".join(iv_char_list)
            iv_hex_str = binascii.b2a_hex(iv_str)
        padding = ord(decoded_str[0])
        start = 0
        if padding < 16:
            for i in range(16):
               start = i
               if ord(decoded_str[i]) > padding:
                   break
        decoded_str = decoded_str[:-start:-1]
        return decoded_str

if __name__ == "__main__":
    po = PaddingOracle()
    good_cipher = sys.argv[1]; # "f20bdba6ff29eed7b046d1df9fb7000058b1ffb4210a580f748b4ac714c001bd4a61044426fb515dad3f21f08aa577c0bdf302936266926ff37dbf7035d5eeb4"
    decoded_text = "Decoded text is:\n"
    for i in range(64, len(good_cipher)+1-64, 32):
        decoded_text = decoded_text + po.decode(good_cipher[i:i+32], good_cipher[i+32:i+64])
    print decoded_text
