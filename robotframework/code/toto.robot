*** Settings ***
Library    toto.py

*** Variables ***
${MESSAGE}    hello world, this is INTERCAL and LOLCODE

*** Test Cases ***
Go Shopping Like A Tard
    Add Element To Bag    ${MESSAGE}
    Add Element To Bag    shoes
    Add Element To Bag    t-shirt
    Display Elements Of Bag

*** Keywords ***
Add Element To Bag
    [Arguments]    ${item}
    toto.Add To Bag    ${item}

Display Elements Of Bag
    toto.Display Bag
