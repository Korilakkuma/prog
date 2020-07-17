<?php

$results = [];

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (!empty($_FILES['file'])) {
        /*
        $new = __DIR__ . '/' . $_FILES['file']['name'];
        $old = $_FILES['file']['tmp_name'];

        move_uploaded_file($old, $new);
        */

        foreach ($_FILES['file'] as $key => $value) {
            $results[$key] = htmlspecialchars($value, ENT_QUOTES, 'UTF-8', false);
        }
    }
}

echo json_encode($results);
