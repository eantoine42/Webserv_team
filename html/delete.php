<?php
ini_set('display_errors', 1);
if ($_SERVER['REQUEST_METHOD'] == 'DELETE') {
    // Parse la requête DELETE pour obtenir le nom du fichier
    parse_str(file_get_contents('php://input'), $_DELETE);

    if (isset($_DELETE['filename'])) {
        $filename = $_DELETE['filename'];

        // Chemin complet du fichier
        $file = '/var/www/essai/try/html/uploads/' . basename($filename);
		echo $file;
		echo "\n";

        // Vérifiez si le fichier existe
        if (file_exists($file)) {
            // Supprime le fichier
            if (unlink(realpath($file))) {
                echo 'Le fichier ' . $filename . ' a été supprimé';
            } else {
                echo 'Erreur lors de la suppression du fichier ' . $filename;
            }
        } else {
            echo 'Le fichier ' . $filename . ' n\'existe pas';
        }
    } else {
        echo 'Aucun nom de fichier spécifié';
    }
} else {
    echo 'Méthode non autorisée';
}

