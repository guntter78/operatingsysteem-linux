#! /bin/bash            # run /bin/bash met path naar script als parameter


echo "------------------------------"
echo "Welkom bij de Foto verplaatser!"
echo "------------------------------"


# eerste parameter
dir=$1 # store directory from script parameter in variable
date=$2


if [ -d "$1" ]; then            # -f is for file
  echo "Deze dir is gevonden."

else
  echo "Er is geen map gekozen."
  echo "Het programma sluit zich af."
  echo "------------------------------"
  exit
fi

if [ "$2" == "week" ]; then
  echo ""
  echo "Je hebt gekozen voor week, fotos worden verplaats op week."
  echo ""

elif [ "$2" == "maand" ]; then
  echo ""
  echo "Je hebt gekozen voor maand, fotos worden verplaats op maand."
  echo ""

else
  echo "Je hebt geen keuze genomen. Start de shell weer opnieuw met als tweede parameter week of maand."
  echo "--------------------------"
fi

if [ "$2" == "maand" ]; then
  for i in $dir/*
  do
    creationdate=$(ls -l --time-style='+%m' "$i" | awk '{print $6}')
    if [ -d "foto/maand/maand-$creationdate" ]; then
      echo "$i fotos worden gekopieerd in foto/maand/maand$creationdate"
      cp "$i" foto/maand/maand-$creationdate
      echo "--------------------------"

      else

      echo "dir foto/maand/maand-$creationdate wordt aangemaakt"
      mkdir foto/maand/maand-$creationdate
      echo "$i fotos worden gekopieerd in foto/maand/maand-$creationdate"
      cp "$i" foto/maand/maand-$creationdate
      echo "--------------------------"

      fi
      originalhash=$(sudo md5sum "$i" | cut -d " " -f1)
      basename=$(basename "$i")
      newhash=$(sudo md5sum foto/maand/maand-$creationdate/$basename | cut -d " " -f1)

      if [ "$originalhash" == "$newhash" ]; then
        rm "$i"
      else
        echo "$i is niet goed."

      fi
  done

else
  for i in $dir/*
  do
    creationdate=$(ls -l --time-style='+%W' "$i" | awk '{print $6}')
    if [ -d "foto/weken/week-$creationdate" ]; then
      echo "$i fotos worden gekopieerd in foto/week/week$creationdate."
      cp "$1"  foto/weken/week-$creationdate
      echo "------------------------------"

    else

    echo "dir foto/weken/week-$creationdate wordt aangemaakt."
    mkdir foto/weken/week-$creationdate
    echo "$i fotos worden gekopieerd in foto/weken/week-$creationdate."
    cp "$i" foto/weken/week-$creationdate
    echo "------------------------------"

    fi

    echo "Nu wordt gecheckt of er een md5 er op zit."
    originalhash=$(sudo md5sum "$i" | cut -d " " -f1)
    basename=$(basename "$i")
    newhash=$(sudo md5sum foto/weken/week-$creationdate/$basename | cut -d " " -f1)

    if [ "$originalhash" == "$newhash" ]; then
      rm "$i"
    else
      echo "$i is niet goed gegaan met hashen."
      echo "------------------------------"
    fi
  done
fi
exit
