
@echo off

CALL :assert "0" , "0"
CALL :assert "42" , "42"
echo "OK"

EXIT /B %ERRORLEVEL%

:assert
SET expected="%~1"
SET input="%~2"
main "%input%" > tmp.s || EXIT /B %ERRORLEVEL%
gcc "-static" "-o" "tmp.exe" "tmp.s"
tmp
SET actual="%?%"
IF "%actual%" "=" "%expected%" (
  echo "%input% => %actual%"
) ELSE (
  echo "%input% => %expected% expected, but got %actual%"
  exit "1"
)
EXIT /B 0
