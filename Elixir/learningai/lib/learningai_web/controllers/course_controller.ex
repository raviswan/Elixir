  defmodule LearningaiWeb.CourseController do
  use LearningaiWeb, :controller

  alias Learningai.Instructors
  alias Learningai.Instructors.Course
  alias Learningai.Repo

  plug LearningaiWeb.Plugs.RequireAuth when action in [:new, :create, :edit, :update, :delete ]
  plug :check_course_owner when action in [:update, :edit, :delete]

  def index(conn, _params) do
    IO.inspect(conn.assigns)
    courses = Instructors.list_courses()
    render(conn, "index.html", courses: courses)
  end

  def new(conn, _params) do
    changeset = Instructors.change_course(%Course{})
    render(conn, "new.html", changeset: changeset)
  end

  def create(conn, %{"course" => course_params}) do
    #case Instructors.create_course(course_params) do
    case Instructors.create_course_with_user(conn.assigns.user, course_params) do
      {:ok, course} ->
        conn
        |> put_flash(:info, "Course created successfully.")
        |> redirect(to: course_path(conn, :show, course))
      {:error, %Ecto.Changeset{} = changeset} ->
        render(conn, "new.html", changeset: changeset)
    end
  end

  def show(conn, %{"id" => id}) do
    course = Instructors.get_course!(id)
    render(conn, "show.html", course: course)
  end

  def edit(conn, %{"id" => id}) do
    course = Instructors.get_course!(id)
    changeset = Instructors.change_course(course)
    render(conn, "edit.html", course: course, changeset: changeset)
    #render(conn, "edit_content.html", course: course, changeset: changeset)

  end

  def update(conn, %{"id" => id, "course" => course_params}) do
    course = Instructors.get_course!(id)

    case Instructors.update_course(course, course_params) do
      {:ok, course} ->
        conn
        |> put_flash(:info, "Course updated successfully.")
        |> redirect(to: course_path(conn, :show, course))
      {:error, %Ecto.Changeset{} = changeset} ->
        render(conn, "edit.html", course: course, changeset: changeset)
    end
  end

  def delete(conn, %{"id" => id}) do
    course = Instructors.get_course!(id)
    {:ok, _course} = Instructors.delete_course(course)

    conn
    |> put_flash(:info, "Course deleted successfully.")
    |> redirect(to: course_path(conn, :index))
  end

  def check_course_owner(conn, _plugparams) do
    #This :params is courtesy "resource" controller helper. It pulls "id" out of the url and attach it to connect   
    # object under params.id property
    %{params: %{"id" => course_id}} = conn

    #Fetch the user id for the course id specified in the url and see if it equals the current user id,
    #let connection through, else reject
    if Repo.get(Course, course_id).user_id == conn.assigns.user.id do
      conn
    else
      conn
      |> put_flash(:error, "You cannot modify  that")
      |> redirect(to: course_path(conn, :index))
      |> halt()

    end
  end

end
