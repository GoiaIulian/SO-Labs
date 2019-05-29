#!/bin/bash

 who | awk '{print($1);}' > logged.txt
