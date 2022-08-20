# CTFD-automation
## Discription
c code to automaticly add challanges into ctfd by creating the nessesery zip file

## file structure
### file discription
in order for the files to be generated properly each catagory must have its own folder that contains a folder for each challange that has all necessery challanges in a README.md file README.md files will be ignored in the rest of the file structure and anything thats not a README.md file will be ignored within the challange folder e.g. setup files and docker images.

### exsample
```
+---main-CTF-folder
|   /README.md *(ignored)*
|   +---Web
|   |   /README.md *(ignored)*
|   |   +---WebChallange1
|   |   |   \README.md
|   |   |   \setup.txt *(ignored)*
|   |   +---WebChallange2
|   |   |   \README.md
|   |   |   \DockerFile *(ignored)*
|   |   |   +---DockerSrc *(ignored)*
|   |   |   |   \index.php *(ignored)*
|   +---Crypto
|   |   +---CryptoChallange1
|   |   |   \README.md
|   |   +---CryptoChallange2
|   |   |   \README.md
```
## README.md structure
each README.md within the challange README.md files is made up of of keys represented by heading 2 size and values contained within code blocks
### table of all keys possible
| key         | discription                                                               | alternitive key | 
|-------------|---------------------------------------------------------------------------|-----------------|
| discription | the markdown that will be displayed to the user whn opening the challange | Description     |
| soulution   | in current verson ignored and skipped                                     | Solution        |
| flag        | the flag that solves the challange (in future to develop regex support    | Flag            |
| points      | the amount of pouints to be gifted con challange completion               | Points          |
| hints       | not implumented yet                                                       | Hints           |
| files       | not implumented yet                                                       | Files           |


### exsample
``````
# title
## discription:
```
the description that will be shown to users for the challange
```
## flag:
```
the solution to the challange
```
## Points:
```
the amount of points the challange is worth
```
``````
