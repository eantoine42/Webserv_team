<?php
ini_set('display_errors', 1);
if(isset($_FILES['fichier']))
{ 
     $dossier = 'uploads/';
     $fichier = basename($_FILES['fichier']['name']);
	 echo   $_FILES['fichier']['tmp_name'];
     if(move_uploaded_file($_FILES['fichier']['tmp_name'], $dossier. $fichier)) //Si la fonction renvoie TRUE, c'est que ça a fonctionné...
     {
          echo 'Upload effectué avec succès !';
     }
     else //Sinon (la fonction renvoie FALSE).
     {
          echo 'Echec de l\'upload !';
     }
}
?>