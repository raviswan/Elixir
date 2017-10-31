defmodule Learningai.InstructorsTest do
  use Learningai.DataCase

  alias Learningai.Instructors

  describe "courses" do
    alias Learningai.Instructors.Course

    @valid_attrs %{name: "some name"}
    @update_attrs %{name: "some updated name"}
    @invalid_attrs %{name: nil}

    def course_fixture(attrs \\ %{}) do
      {:ok, course} =
        attrs
        |> Enum.into(@valid_attrs)
        |> Instructors.create_course()

      course
    end

    test "list_courses/0 returns all courses" do
      course = course_fixture()
      assert Instructors.list_courses() == [course]
    end

    test "get_course!/1 returns the course with given id" do
      course = course_fixture()
      assert Instructors.get_course!(course.id) == course
    end

    test "create_course/1 with valid data creates a course" do
      assert {:ok, %Course{} = course} = Instructors.create_course(@valid_attrs)
      assert course.name == "some name"
    end

    test "create_course/1 with invalid data returns error changeset" do
      assert {:error, %Ecto.Changeset{}} = Instructors.create_course(@invalid_attrs)
    end

    test "update_course/2 with valid data updates the course" do
      course = course_fixture()
      assert {:ok, course} = Instructors.update_course(course, @update_attrs)
      assert %Course{} = course
      assert course.name == "some updated name"
    end

    test "update_course/2 with invalid data returns error changeset" do
      course = course_fixture()
      assert {:error, %Ecto.Changeset{}} = Instructors.update_course(course, @invalid_attrs)
      assert course == Instructors.get_course!(course.id)
    end

    test "delete_course/1 deletes the course" do
      course = course_fixture()
      assert {:ok, %Course{}} = Instructors.delete_course(course)
      assert_raise Ecto.NoResultsError, fn -> Instructors.get_course!(course.id) end
    end

    test "change_course/1 returns a course changeset" do
      course = course_fixture()
      assert %Ecto.Changeset{} = Instructors.change_course(course)
    end
  end
end
