program poisson
  ! Fortran program to solve the two-dimensional Poisson equation on
  ! a uint square using one-dimensional eigenvalue decompositions
  ! and fast sine transforms.
  !
  ! Einar M. Rønquist
  ! NTNU, October 2000
  ! Revised by Eivind Fonn, February 2015

  ! The number of grid points in each direction is n+1
  ! The number of degrees of freedom in each direction is n-1
  parameter (n = 128)
  parameter (m = n - 1)
  parameter (nn = 4 * n)

  real*8 grid(0:n), diag(m), b(m,m), bt(m,m)
  real*8 pi
  real*8 z(0:nn-1)
  real*4 tarray(2), t1, t2, dt

  h = 1.0 / n
  pi = 4.0 * atan(1.0)

  ! Grid points
  do i=0,n
     grid(i) = i * h
  end do

  ! The diagonal of the eigenvalue matrix of T
  do i=1,m
     diag(i) = 2.0 * (1.0 - cos(i * pi / n))
  end do

  ! Initialize the right hand side data
  do j=1,m
     do i=1,m
        b(i,j) = h * h * rhs(grid(i), grid(j))
     end do
  end do

  ! Calculate Btilde^T = S^-1 * (S * B)^T
  do j=1,m
     call fst(b(1,j), n, z, nn)
  end do
  call transpose(bt, b, m)
  do i=1,m
     call fstinv(bt(1,i), n, z, nn)
  end do

  ! Solve Lambda * Xtilde = Btilde
  do j=1,m
     do i=1,m
        bt(i,j) = bt(i,j) / (diag(i) + diag(j))
     end do
  end do

  ! Calculate X = S^-1 * (S * Xtilde^T)
  do i=1,m
     call fst(bt(1,i), n, z, nn)
  end do
  call transpose(b, bt, m)
  do j=1,m
     call fstinv(b(1,j), n, z, nn)
  end do

  ! Calculate maximal value of solution
  umax = 0.0
  do j=1,m
     do i=1,m
        if (b(i,j) .gt. umax) umax = b(i,j)
     end do
  end do

  write(6,*) umax

  stop
end program poisson


subroutine transpose(at, a, m)
  real*8 a(m,m), at(m,m)
  do j=1,m
     do i=1,m
        at(j,i) = a(i,j)
     end do
  end do
  return
end subroutine transpose


function rhs(x, y)
  real*8 x, y
  rhs = 2 * (y - y*y + x - x*x)
end function rhs
