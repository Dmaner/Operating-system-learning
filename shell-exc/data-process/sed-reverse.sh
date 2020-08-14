#!/bin/bash
sed -n '{1!G ; h ; $p }' ./data-process/test2.txt