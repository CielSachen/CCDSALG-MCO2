$pathSep = [System.IO.Path]::DirectorySeparatorChar

$sourceDirPaths = ".$($pathSep)app", ".$($pathSep)include", ".$($pathSep)src"
$sourceFileExts = "*.c", "*.h"

$outDirName = "dist"
$outDirPath = ".$($pathSep)$($outDirName)"

if (-not(Test-Path -Path $outDirPath)) {
  New-Item -Path "." -Name $outDirName -ItemType "Directory" -Force | Out-Null

  Write-Output -InputObject "Created: $($outDirPath)"

  Write-Output -InputObject ""
}

Write-Output -InputObject "Copying from $($sourceDirPaths -join ", ") to $($outDirPath)"

Get-ChildItem -Path $sourceDirPaths -Include $sourceFileExts -File -Recurse |
ForEach-Object -Process {
  Copy-Item -Path $_.FullName -Destination $outDirPath

  Write-Output -InputObject "  Copied: $($_.Name)"
}

Write-Output -InputObject ""

Write-Output -InputObject "Fixing source file #include directives"

Get-ChildItem -Path $outDirPath -Include $sourceFileExts[0] -File -Recurse |
ForEach-Object -Process {
  (Get-Content -Path $_.FullName) -replace "#include `"[A-Za-z_]+\/", "#include `"" | Set-Content -Path $_.FullName

  Write-Output -InputObject "  Updated: $($_.Name)"
}
