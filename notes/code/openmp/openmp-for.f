!OMP DO SCHEDULE(STATIC)
do i = 1,100
  call DoSomething(i)
end do
!OMP END DO
