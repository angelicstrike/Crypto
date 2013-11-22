import Data.List
import Data.List.Split
import Data.Text (pack, breakOnAll, Text)
import Data.Function

--James Gross
--MATH 4175, CRN 94509

--These are the ciphers to decrypt, think of these as constants
cipher1 = "UVWWVX YZAYZ AX BX CXUVWWVU DZERZZ ZY FGBH HGZ FVIJD UBKKY FZYDVW"
cipher2 = "GYOMX NOGNG QUGNE TNMXM PLMZO MXYMK TMMJO XAXEN TKZZM QEBMF TZEQK JKZQE XYEXN MQLJK NOXAN HMTJE EFETX MICXE IJMFA MIHOY HMKYH WMKZR ZOXAG IONHO N"
cipher5 = "CDCBB XBGBC LZURC WBCWF JVRFQ BXNDU CRLZM ZJRVQ RFFRF"

--This function  removes the spaces from a list of characters
removeChar :: Eq a => a -> [a] -> [a] 
removeChar a xs = filter (/= a) xs

--This function gets the frequency of a list of characters
--It sorts the characters alphabetically
--then removes any spaces
--Then groups the list by characters (so if the list was sorted as 'AAABCCC', we would get
--a list of lists that looked like ['AAA', 'B', 'CCC']
--Then it counts how long each member of the top level list is, and sticks that into the return
--value for the function. 
--It does the above for every character, and at the end we have a single letter frequency list 
singleLetterFrequency :: [Char] -> [(Char, Int)]
singleLetterFrequency [] = []
singleLetterFrequency xs = map (\a -> (head a, length a)) $ group $ removeChar ' ' $ sort xs

--This generates the single letter frequencies for the cipher from problem 1
--It calls the frequency counter function, them sorts the return from that function from most 
--frequent to least frequent.
math4175Prob1Singles :: [(Char, Int)]
math4175Prob1Singles = sortBy (flip compare `on` snd) (singleLetterFrequency cipher1)

--This generates the single letter frequencies for the cipher from problem 2
--It calls the frequency counter function, them sorts the return from that function from most 
--frequent to least frequent.
math4175Prob2Singles :: [(Char, Int)]
math4175Prob2Singles = sortBy (flip compare `on` snd) (singleLetterFrequency cipher2)

--This generates the single letter frequencies for the cipher from problem 5
--It calls the frequency counter function, them sorts the return from that function from most 
--frequent to least frequent.
math4175Prob5Singles :: [(Char, Int)]
math4175Prob5Singles = sortBy (flip compare `on` snd) (singleLetterFrequency cipher5)


