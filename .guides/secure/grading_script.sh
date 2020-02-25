#Creating folder
mkdir ~/workspace/WordrangeStudent
rm -rf ~/workspace/WordrangeStudent/*
# moving relevant files from student's directory to folder
cp ~/workspace/Wordrange/*.cpp ~/workspace/WordrangeStudent  2>/dev/null
cp ~/workspace/Wordrange/*.hpp ~/workspace/WordrangeStudent  2>/dev/null
cp ~/workspace/Wordrange/*.c ~/workspace/WordrangeStudent  2>/dev/null
cp ~/workspace/Wordrange/*.h ~/workspace/WordrangeStudent  2>/dev/null
cp ~/workspace/Wordrange/Makefile ~/workspace/WordrangeStudent  2>/dev/null
cp ~/workspace/Wordrange/README ~/workspace/WordrangeStudent  2>/dev/null
# Run robograder
cd ~/workspace/.guides/secure
python3 robograder.py -e -t 60 WordrangeStudent ~/workspace
cd ~/workspace
score=$( tail -n 1 ~/workspace/WordrangeStudent/WordrangeStudent.log )
echo "$score"
# Show json based passed environment
echo $CODIO_AUTOGRADE_ENV
# Send the grade back to Codio
curl --retry 3 -s "$CODIO_AUTOGRADE_URL&grade=$score"
