<!DOCTYPE html>
<html>
<head>
    <title>Résultat du traitement</title>
</head>
<body>
    <h1>Résultat du traitement</h1>
    <?php
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        $nom = $_POST['nom'];
        $email = $_POST['email'];
        
        echo "<p>Nom : $nom</p>";
        echo "<p>Email : $email</p>";
    } else {
        echo "<p>Aucune donnée reçue.</p>";
    }
    ?>
</body>
</html>