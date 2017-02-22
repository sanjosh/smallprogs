<html>
<head>
<title></title>
</head>
<body>
<form action="/login" method="post">
    Username:<input type="text" name="username"><br>
    Password:<input type="password" name="password"><br>
    Male:<input type="radio" name="gender" value="1">Male<br>
    Female:<input type="radio" name="gender" value="2">Female<br>
    <input type="hidden" name="token" value="{{.}}">
    <input type="submit" value="Login">
</form>
</body>
</html>
