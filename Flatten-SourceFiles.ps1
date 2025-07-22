$path_sep = [System.IO.Path]::DirectorySeparatorChar

$source_dir_paths = ".$($path_sep)app", ".$($path_sep)include", ".$($path_sep)src"
$source_file_exts = "*.c", "*.h"

$out_dir_name = "dist"
$out_dir_path = ".$($path_sep)$($out_dir_name)"

if (-not(Test-Path -Path $out_dir_path)) {
  New-Item -Path "." -Name $out_dir_name -ItemType "Directory" -Force | Out-Null

  Write-Output -InputObject "Created: $($out_dir_path)`n"
}

Write-Output -InputObject "Copying from $($source_dir_paths -join ", ") to $($out_dir_path)"

Get-ChildItem -Path $source_dir_paths -Include $source_file_exts -File -Recurse |
ForEach-Object -Process {
  Copy-Item -Path $_.FullName -Destination $out_dir_path

  Write-Output -InputObject "  Copied: $($_.Name)"
}

Write-Output -InputObject "`nFixing source file #include directives"

Get-ChildItem -Path $out_dir_path -Include $source_file_exts[0] -File -Recurse |
ForEach-Object -Process {
  (Get-Content -Path $_.FullName) -replace "#include `"[A-Za-z_]+\/", "#include `"" | Set-Content -Path $_.FullName

  Write-Output -InputObject "  Updated: $($_.Name)"
}
